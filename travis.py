import os
import subprocess
import json
import requests

reqid = os.environ['TRAVIS_PULL_REQUEST']
js = requests.get('https://api.github.com/repos/valera5505/SPbU/pulls/' + reqid + '/files').json()

for i in range(0, len(js)-1):
    if js[i]['status'] == 'removed':
        continue
    if not js[i]['filename'].endswith('.cpp'):
        continue
    print(js[i]['filename'] + ' is compiling')
    process = subprocess.Popen(['g++', '-o', js[i]['filename'] + '.' + i, js[i]['filename']], stdout=subprocess.PIPE)
    process.wait()

    if not os.path.exists(js[i]['filename'] + '.' + i):
        exit(1)
    
