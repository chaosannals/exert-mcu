# save this as app.py
# pip install Flask
from flask import Flask

app = Flask(__name__)

@app.route("/")
def index():
    return "Hello, World!"

@app.route("/post")
def post_action():
    return 'on Post'

@app.route("/put")
def put_action():
    return 'on Put'

@app.route("/patch")
def patch_action():
    return 'on patch'

@app.route("/delete")
def delete_action():
    return 'on delete'

@app.route("/get")
def head_action():
    return 'on get'

app.run(host='0.0.0.0', port=5000)
