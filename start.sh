python3 -m venv pyenv
. ./pyenv/bin/activate
pip install --upgrade pip
pip install beautifulsoup4 lxml
python3 ~/etc/contests/scripts/testcase_parser/server.py &
rm -rf ~/_
ln -s $PWD ~/_
rm -rf ~/downloads/_
ln -s $PWD ~/downloads/_
