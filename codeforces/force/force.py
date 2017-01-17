#!/usr/bin/python
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
from bs4 import BeautifulSoup

ApiKey = '714a0baaad6b2ea7d18e46363e9ba8583ec26e12'
ApiSecret = '837468f7d6dd95fb25821e344c5c99a11074146d'

parser = argparse.ArgumentParser(description='Ladder')
parser.add_argument('--ladder', action='store_true')
parser.add_argument('-r', '--rating', help='estimated rating')
parser.add_argument('--range', help='rating range - absolute or %', default='2%')
parser.add_argument('--tag', help='problem tag')

parser.add_argument('--open', help='open specific problem', action='store_true')
parser.add_argument('-c', '--contest', help='id of contest')
parser.add_argument('-p', '--problem', help='index of problem')

parser.add_argument('--experiment', action='store_true')
parser.add_argument('--update-problems', action='store_true')
parser.add_argument('--list-tags', action='store_true')

args = parser.parse_args()

# print args

db = sqlite3.connect('codeforces.db')
db.text_factory = str
db.cursor().execute('CREATE TABLE IF NOT EXISTS `api_cache` (url TEXT unique, response TEXT, updated INTEGER)')
db.cursor().execute('CREATE TABLE IF NOT EXISTS `contest` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `name` TEXT NOT NULL UNIQUE )')
db.cursor().execute('CREATE TABLE IF NOT EXISTS `problem` ( `contest_id` TEXT, `problem_index` TEXT, `rating` INTEGER DEFAULT null, `solved` INTEGER NOT NULL DEFAULT 0, `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, `points` INTEGER )')
db.cursor().execute('CREATE TABLE IF NOT EXISTS `tag` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `name` TEXT NOT NULL UNIQUE )')
db.cursor().execute('CREATE TABLE IF NOT EXISTS `problem_tag` ( `problem_id` INTEGER NOT NULL, `tag_id` INTEGER NOT NULL, FOREIGN KEY(`problem_id`) REFERENCES problem, FOREIGN KEY(`tag_id`) REFERENCES tag )')
db.cursor().execute('CREATE UNIQUE INDEX IF NOT EXISTS `unique_cache_url` ON `api_cache` (`url` ASC)')


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
    ''', (key, s, values['time']))
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


def openProblem(contestId, index):
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
    # subprocess.call(["problem", index])
    # subprocess.call(["date"])


def now():
    return int(time.time())

def day():
    return 3600 * 24

# contest -> { handle -> new rating }
def getNewRanksAfter(contestId):
    j = loadJson('contest.ratingChanges',
                        {'contestId': contestId})
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
        result[r['handle']] = r['newRating']
    return result

def getTagId(tag):
    id = db.cursor().execute("""
    SELECT id FROM `tag` WHERE (`name`=?)
    """, (tag, )).fetchone()
    if id:
        return id[0]
    return db.cursor().execute("""
    INSERT INTO `tag` (`name`) VALUES (?)
    """, (tag, )).lastrowid

def saveProblem(p):
    # print('save problem', p)
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
        print('problem %s.%s already exists' % (p['contestId'], p['index']))
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

def rateProblem(index, ranks, rows):
    ranks_of_solvers = []
    for r in rows:
        if int(r['problemResults'][index]['points']) == 0:
            # have not solved the problem
            continue
        for member in r['party']['members']:
            if member['handle'] in ranks:
                ranks_of_solvers.append(ranks[member['handle']])
            else:
                print('rank of %s is not found' % (member, ))
    ranks_of_solvers.sort()
    n = len(ranks_of_solvers)
    if n == 0:
        return None
    return ranks_of_solvers[int((n * 5) / 100)] # 95 %


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
    for i in range(len(problems)):
        p = problems[i]
        rating = rateProblem(i, ranks, rows)
        if not rating:
            continue
        problemId = saveProblem(p)
        if not problemId:
            continue
        print('%s %s = %s' % (p['contestId'], p['index'], rating, ))
        db.cursor().execute('''
        UPDATE `problem` SET `rating`=? WHERE `id`=?
        ''', (rating, problemId))


def listTags():
    rows = db.cursor().execute('SELECT `name` FROM `tag` ORDER BY `name`').fetchall()
    for r in rows:
        print(r[0])

def main():
    if (args.update_problems):
        updateProblems()
        exit(0)

    if (args.open):
        openProblem(args.contest, args.problem)
        exit(0)

    if (args.ladder):
        selectBestProblem()
        exit(0)

    if (args.list_tags):
        listTags()
        exit(0)

    parser.print_usage()

def isAlredySolved(contestId, problemIndex):
    return os.path.exists("%s/%s.cc" % (contestId, problemIndex)) or os.path.exists("%s/%s.cpp" % (contestId, problemIndex))


def selectBestProblem():
    solved = int(args.rating)
    range = args.range
    if '%' in str(range):
        range = range[:range.find('%')]
        range = int(range) * solved / 100
    else:
        range = int(range)
    print('searching for problem with rating %d +- %d' % (solved, range))
    query = '''SELECT p.`id`, `contest_id`, `problem_index`, `rating` FROM `problem` p '''
    where = '''WHERE (rating >= ?) AND (rating <= ?) AND (solved = 0) '''
    query_args = [solved - range, solved + range, ]
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
        problemId = p[2]
        rating = p[3]
        if isAlredySolved(contestId, problemId):
            print('%s.%s is already solved' % (contestId, problemId))
            db.cursor().execute('''UPDATE problems SET solved = 1 WHERE `id`= ?''', (id,))
            db.commit()
            continue
        print('opening %s.%s with rating %d' % (contestId, problemId, rating))
        openProblem(contestId, problemId)
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
        print(c['id'], c['name'])
        row = db.cursor().execute('SELECT `id` FROM `contest` WHERE `name`=?', (c['id'],)).fetchone()
        if row:
            print('analyzed')
            continue
        analyzeContest(c['id'])
        db.cursor().execute('''
            INSERT INTO `contest` (`name`) VALUES (?)
            ''', (c['id'],))
        db.commit()


if __name__ == '__main__':
    main()

