# pip install beautifulsoup4
# 
import time
import urllib
import urllib.parse
import urllib.request
import urllib.error
# import urllib.query
import hashlib
import json
import os
import argparse
import random
import webbrowser
import sqlite3
import subprocess
import math
from bs4 import BeautifulSoup

ApiKey = os.environ['CODEFORCES_API_KEY']
ApiSecret = os.environ['CODEFORCES_API_SECRET']
handle = os.environ['CODEFORCES_HANDLE']

parser = argparse.ArgumentParser(description='codeforces problem picker', formatter_class=argparse.RawTextHelpFormatter)
# parser.add_argument('--', help())
parser.add_argument('--rating', '-r', help='your current estimated elo, any string\n`+` and `-` characters increase or decrease rating 20 points\ne.g. `+++` will add 60 points\n`=` (or any string w/o +-) does not change elo and shows current')
parser.add_argument('--open', '-o', help='open problem\n`last` - last opened\n`next` - unsolved problem with your current rating\n`502.B` - B from contest 500\n`1830` - with specific rating')
parser.add_argument('--range', help='rating selection range - absolute or %%, e.g. `2%%` (default), `32`', default='2%')
parser.add_argument('--tag', help='problem tag')
parser.add_argument('--list-tags', action='store_true', help='list all tags available')
parser.add_argument('--done', '-d', help='mark last opened problem as solved', action='store_true')
parser.add_argument('--update-problems', action='store_true', help='update problem set from codeforces.com')

args = parser.parse_args()

# print(args)
# exit(0)

db = sqlite3.connect('codeforces.db')
db.text_factory = str
db.cursor().execute('CREATE TABLE IF NOT EXISTS `api_cache` (url TEXT unique, response TEXT, updated INTEGER)')
db.cursor().execute('CREATE TABLE IF NOT EXISTS `contest` ( `id` TEXT NOT NULL UNIQUE, `name` TEXT)')
db.cursor().execute('''CREATE TABLE IF NOT EXISTS `problem` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `contest_id` TEXT,
`problem_index` TEXT, `rating` INTEGER DEFAULT null,
`points` INTEGER )''')
db.cursor().execute('CREATE TABLE IF NOT EXISTS `tag` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `name` TEXT NOT NULL UNIQUE )')
db.cursor().execute('CREATE TABLE IF NOT EXISTS `problem_tag` ( `problem_id` INTEGER NOT NULL, `tag_id` INTEGER NOT NULL, FOREIGN KEY(`problem_id`) REFERENCES problem, FOREIGN KEY(`tag_id`) REFERENCES tag )')
db.cursor().execute('CREATE UNIQUE INDEX IF NOT EXISTS `unique_cache_url` ON `api_cache` (`url` ASC)')
db.cursor().execute('CREATE TABLE IF NOT EXISTS `user` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, `rating` INTEGER, `handle` TEXT UNIQUE )')
db.cursor().execute('CREATE TABLE IF NOT EXISTS `user_problem` ( `user_id` INTEGER NOT NULL, `problem_id` INTEGER NOT NULL, `solved` INTEGER, `opened` INTEGER)')


def params(values):
    params = list(values.items())
    # print(values, params)
    params.sort()
    s = ''
    for p in params:
        a = p[0] + '=' + urllib.parse.quote(str(p[1]))
        if s == '':
            s = '?' + a
        else:
            s = s + '&' + a
    return s


def apiCall(method, values, expire=0):
    url = 'http://codeforces.com/api/' + method
    key = url + params(values)
    cursor = db.cursor()
    cursor.execute('''SELECT response FROM api_cache WHERE url=? AND updated > ?''', (key, expire))
    cached = cursor.fetchone()
    if not cached is None:
        # print 'api call cached'
        return cached[0]
        # print 'cached', cached
    print(key)
    rand = '123456'
    now = int(time.time())
    values['apiKey'] = ApiKey
    values['time'] = int(time.time())
    hash = rand + '/' + method + params(values) + '#' + ApiSecret
    hash = hashlib.sha512(hash.encode('utf-8')).hexdigest()
    while len(hash) < 128:
        hash = '0' + hash
    values['apiSig'] = rand + hash
    url += params(values)
    time.sleep(1)  # to prevent spam of API
    req = urllib.request.Request(url)
    try:
        response = urllib.request.urlopen(req)
    except urllib.error.HTTPError as err:
        print("URL error", err)
        return None
    s = response.read()
    cursor.execute('''
      DELETE FROM api_cache WHERE (url=?)
  ''', (key,))
    cursor.execute('''
    INSERT INTO api_cache(url, response, updated) VALUES (?,?,?)
    ''', (key, s, now))
    db.commit()
    return s

def loadJson(method, values, expire=0):
    j = apiCall(method, values, expire)
    if not j:
        return None
    return json.loads(j)

def problemUrl(contestId, index):
    return 'http://codeforces.com/contest/%s/problem/%s' % \
           (contestId, index)

def getProblemId(contestId, problemName):
    row = db.cursor().execute('''SELECT id FROM problem
    WHERE contest_id=? AND problem_index=?''', [contestId, problemName]).fetchone()
    if row is None:
        return None
    return row[0]

def getProblemInfo(problemId):
    return db.cursor().execute('''
    SELECT contest_id, problem_index FROM problem WHERE id=?
    ''', (problemId, )).fetchone()

def openProblem(contestId, index):
    problemId = getProblemId(contestId, index)
    if problemId:
        status = getProblemStatus(problemId)
        status['opened'] = now()
        saveProblemStatus(status)
    url = problemUrl(contestId, index)
    webbrowser.open(url)
    if not os.path.exists(contestId):
        os.makedirs(contestId)
    os.chdir(contestId)
    if not os.path.exists(index + '.in') and \
            not os.path.exists(index + '.in.out'):
        with open(index + '.in', 'w') as in_file, \
                open(index + '.in.out', 'w') as out_file:
            html = urllib.request.urlopen(url)
            soup = BeautifulSoup(html, 'lxml')
            inputs = soup.find_all('div', attrs={'class': 'input'})
            outputs = soup.find_all('div', attrs={'class': 'output'})
            samples = zip(inputs, outputs)
            for s in samples:
                for i in s[0].find('pre').strings:
                    in_file.write(str(i).strip())
                    in_file.write('\n')
                for i in s[1].find('pre').strings:
                    out_file.write(str(i).strip())
                    out_file.write('\n')
    subprocess.call(["C:\\Program Files\\Git\\bin\\bash.exe", '-c', '/c/Users/mgoncharov/etc/contests/problem.sh %s' % (index)])
    subprocess.call(["date"])

def now():
    return int(time.time())

def day():
    return 3600 * 24

# contest -> { handle -> new rating }
def getNewRanksAfter(contestId):
    j = loadJson('contest.ratingChanges', {'contestId': contestId})
    # {
    #     "status": "OK",
    #     "result": [
    #         {
    #             "contestId": 566,
    #             "contestName": "VK Cup 2015 - Finals, online mirror",
    #             "handle": "rng_58",
    #             "rank": 1,
    #             "ratingUpdateTimeSeconds": 1438284000,
    #             "oldRating": 2849,
    #             "newRating": 2941
    #         },
    if not j or j['status'] != 'OK':
        print('failed to load contest %s ranks ' % (contestId))
        return None
    result = {}
    for r in j['result']:
        result[r['handle']] = int(r['newRating'])
    return result

def getTagId(tag):
    if 'name' in tag:
        tag = tag['name']
    id = db.cursor().execute("""
    SELECT id FROM `tag` WHERE (`name`=?)
    """, (tag, )).fetchone()
    if id:
        return id[0]
    return db.cursor().execute("""
    INSERT INTO `tag` (`name`) VALUES (?)
    """, (tag, )).lastrowid

def saveProblem(p):
    # {
    #     "contestId": 566,
    #     "index": "A",
    #     "name": "Matching Names",
    #     "type": "PROGRAMMING",
    #     "points": 1750,
    #     "tags": [
    #         "dfs and similar",
    #         "strings",
    #         "trees"
    #     ]
    # },
    if ('contestId' not in p) or ('index' not in p):
        print('bad problem')
        return None
    row = db.cursor().execute('''
        SELECT `id` FROM `problem` WHERE (`contest_id`=?) AND (`problem_index`=?)
    ''', (p['contestId'], p['index'])).fetchone()
    if row:
        return row[0]
    cursor = db.cursor()
    points = 1
    if 'points' in p:
        points = int(p['points'])
    id = cursor.execute('''
        INSERT INTO `problem` (`contest_id`, `problem_index`, `points`) VALUES (?, ?, ?)
    ''', ((p['contestId'], p['index'], points,))).lastrowid
    # print('new problem id', id)
    if 'tags' in p:
        for t in p['tags']:
            db.cursor().execute('''
            INSERT INTO `problem_tag` (`problem_id`, `tag_id`) VALUES (?, ?)
            ''', (id, getTagId(t)))
    return id

# probability that r1 beats r2
def win_probability(r1, r2):
    return 1.0 / (1.0 + math.pow(10.0, (r2-r1) / 400.0))

def rateProblem(index, rows, solvedOne):
    solved = 0
    for r in rows:
        for member in r['party']['members']:
            if int(r['problemResults'][index]['points']) != 0:
                solved += 1
    k = len(solvedOne)
    if solved == 0:
        return None
    low = solvedOne[0]
    high = solvedOne[-1]
    step = (high - low) // 2
    while (step > 0):
        m = low + step
        total = 0.0
        for r in solvedOne:
            total += win_probability(float(r), float(m))
        if total > solved:
            low = m
        step = step // 2
    return low

def analyzeContest(contestId):
    standings = loadJson('contest.standings', {'contestId': contestId})
    if not standings:
        return False
    # {
    #     "status": "OK",
    #     "result" : {
    #         "contest": {},
    #         "problems": [
    #             {
    #                 "contestId": 566,
    #                 "index": "A",
    #                 "name": "Matching Names",
    #                 "type": "PROGRAMMING",
    #                 "points": 1750,
    #                 "tags": [
    #                     "dfs and similar",
    #                     "strings",
    #                     "trees"
    #                     {"name": "binary search"}
    #                 ]
    #             },
    #         ,...]
    #         "rows": [
    #             {
    #                 "party": {
    #                     "contestId": 566,
    #                     "members": [
    #                         {
    #                             "handle": "rng_58"
    #                         }
    #                     ],
    #                     "participantType": "CONTESTANT",
    #                     "ghost": false,
    #                     "room": 8,
    #                     "startTimeSeconds": 1438273200
    #                 },
    #                 "rank": 1,
    #                 "points": 7974,
    #                 "penalty": 0,
    #                 "successfulHackCount": 1,
    #                 "unsuccessfulHackCount": 0,
    #                 "problemResults": [
    #                     {
    #                         "points": 1330,
    #                         "rejectedAttemptCount": 0,
    #                         "type": "FINAL",
    #                         "bestSubmissionTimeSeconds": 3624
    #                     },
    #     , ...}
    # }
    if standings['status'] != 'OK':
        print('bad status of contest %s' % contestId)
        return False
    standings = standings['result']
    problems = standings['problems']
    ranks = getNewRanksAfter(contestId)
    if not ranks:
        print('no rank changes')
        return True  # not every contest changes ranks
    rows = standings['rows']
    solvedOne = []
    # only interested in people who solved at least one correctly
    for r in rows:
        for member in r['party']['members']:
            if member['handle'] in ranks:
                solvedOne.append(ranks[member['handle']])
            # for p in r['problemResults']:
                # if p['points'] != 0:
                    # if member['handle'] in ranks:
                    # break
            # break
    solvedOne.sort()
    # remove outsiders
    # solvedOne = solvedOne[(len(solvedOne) * 2 // 100):]
    for i in range(len(problems)):
        p = problems[i]
        rating = rateProblem(i, rows, solvedOne)
        if not rating:
            continue
        problemId = saveProblem(p)
        if not problemId:
            continue
        print('%s %s = %s' % (p['contestId'], p['index'], rating, ))
        db.cursor().execute('''
        UPDATE `problem` SET `rating`=? WHERE `id`=?
        ''', (rating, problemId))
        # committed later


def listTags():
    rows = db.cursor().execute('SELECT `name` FROM `tag` ORDER BY `name`').fetchall()
    for r in rows:
        print(r[0])

def getUserId(handle):
    row = db.cursor().execute('SELECT `id` FROM `user` WHERE `handle`=?', (handle,)).fetchone()
    if row:
        return row[0]
    id = db.cursor().execute('INSERT INTO `user` (`rating`, `handle`) VALUES(?, ?)', (1300, handle)).lastrowid
    db.commit()
    return id

def getUserRating(handle):
    id = getUserId(handle)
    return db.cursor().execute('SELECT `rating` FROM `user` WHERE `id`=?', (id,)).fetchone()[0]

def setUserRating(handle, rating):
    id = getUserId(handle)
    db.cursor().execute('UPDATE `user` SET `rating`=? WHERE `id`=?', (rating, id, ))
    db.commit()

def getLastProblemId():
    return db.cursor().execute('''SELECT up.problem_id FROM user_problem up
    WHERE up.user_id = ? ORDER BY up.opened DESC LIMIT 1''',
                               (getUserId(handle), )).fetchone()[0]

def main():
    if (args.update_problems):
        updateProblems()
        exit(0)

    if (args.done):
        id = getLastProblemId()
        status = getProblemStatus(id)
        if status['solved']:
            print(getProblemInfo(id), "already marked as solved")
        else:
            print(getProblemInfo(id), "marked as solved")
            status['solved'] = now()
            saveProblemStatus(status)

    if (args.rating):
        diff = 0
        for c in args.rating:
            if c == '-':
                diff -= 20
            if c == '+':
                diff += 20
        r = getUserRating(handle)
        setUserRating(handle, r + diff)
        print('current rating is %d (%s%d)' % (r + diff, ('+' if (diff >= 0) else ''), diff))

    if (args.open):
        if args.open == 'last':
            parts = getProblemInfo(getLastProblemId())
            openProblem(parts[0], parts[1])
            exit(0)
        if args.open == 'next':
            selectBestProblem(getUserRating(handle))
            exit(0)
        if '.' in args.open:
            parts = args.open.split('.')
            if len(parts) == 2:
                openProblem(parts[0], parts[1])
                exit(0)
        else:
            selectBestProblem(int(args.open))
            exit(0)

    if (args.list_tags):
        listTags()
        exit(0)

    if (not args.done and not args.rating):
        parser.print_usage()

def isProblemFileExist(contestId, problemIndex):
    return os.path.exists("%s/%s.cc" % (contestId, problemIndex)) or os.path.exists("%s/%s.cpp" % (contestId, problemIndex))

def problemStatusRow(problemId):
    return db.cursor().execute('''
    SELECT problem_id, user_id, solved, opened
    FROM user_problem
    WHERE `user_id`=? AND `problem_id`=?''',
    (getUserId(handle),problemId,)).fetchone()

def getProblemStatus(id):
    row = problemStatusRow(id)
    if row is None:
        db.cursor().execute('''INSERT INTO user_problem (user_id, problem_id)
        VALUES (?, ?)''', (getUserId(handle), id))
        db.commit()
        row = problemStatusRow(id)
    return {'problem_id': row[0],
            'user_id': row[1],
            'solved': row[2],
            'opened': row[3]}

def saveProblemStatus(status):
    db.cursor().execute('''
    UPDATE user_problem
    SET solved=?, opened=?
    WHERE problem_id=? AND user_id=?''',
    (status['solved'], status['opened'], status['problem_id'], status['user_id']))
    db.commit()

def selectBestProblem(rating):
    userId = getUserId(handle)
    range = args.range
    if '%' in str(range):
        range = range[:range.find('%')]
        range = int(range) * rating / 100
    else:
        range = int(range)
    print('searching for problem with rating %d +- %d' % (rating, range))
    query = '''
    SELECT p.`id`, `contest_id`, `problem_index`, `rating`
    FROM `problem` p
    LEFT JOIN user_problem up ON (up.problem_id = p.id)
    AND (up.solved IS NULL)
    AND (up.user_id = ?)'''
    where = '''WHERE (rating >= ?) AND (rating <= ?)'''
    query_args = [userId, rating - range, rating + range, ]
    if args.tag:
        print('and tag "%s"' % (args.tag, ))
        query += 'JOIN `problem_tag` pt ON (pt.problem_id=p.id) JOIN tag t ON (t.id=pt.tag_id) '
        where += ' AND (t.`name`=?)'
        query_args.append(args.tag)
    problems = db.cursor().execute(query + where, query_args).fetchall()
    random.shuffle(problems)
    print('%d problems found' % (len(problems)))
    for p in problems:
        id = p[0]
        contestId = p[1]
        problemName = p[2]
        rating = p[3]
        statusRow = problemStatusRow(id)
        if isProblemFileExist(contestId, problemName) and (not statusRow):
            print('%s.%s looks like already solved' % (contestId, problemName))
            status = getProblemStatus(id)
            status.solved = 0
            status.attepted = 0
            saveProblemStatus(status)
            continue
        print('opening %s.%s with rating %d' % (contestId, problemName, rating))
        openProblem(contestId, problemName)
        exit(0)
    print('no matched problems')
    exit(1)


def updateProblems():
    contests = loadJson('contest.list', {}, now() - 3600)
    if not contests:
        exit(1)
    # example:
    # {
    #     "status": "OK",
    #     "result": [
    #         {
    #             "id": 755,
    #             "name": "8VC Venture Cup 2017 - Elimination Round",
    #             "type": "CF",
    #             "phase": "FINISHED",
    #             "frozen": false,
    #             "durationSeconds": 7200,
    #             "startTimeSeconds": 1484499900,
    #             "relativeTimeSeconds": 142562
    #         },
    #     ]
    # }
    ###
    for c in contests['result']:
        if c['phase'] != "FINISHED":
            continue
        # maybe results are not ready yet
        if (c['durationSeconds'] + c['startTimeSeconds'] + day() > now()):
            continue
        row = db.cursor().execute('SELECT `id` FROM `contest` WHERE `id`=?', (c['id'],)).fetchone()
        if row:
            # print('analyzed')
            continue
        print(c['id'], c['name'])
        analyzeContest(c['id'])
        db.cursor().execute('''
            INSERT INTO `contest` (`id`, `name`) VALUES (?, ?)
            ''', (c['id'],c['name'],))
        db.commit()


if __name__ == '__main__':
    main()
