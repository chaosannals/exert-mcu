# save this as app.py
# pip install Flask
from flask import Flask

app = Flask(__name__)

@app.get("/")
def index():
    return "Hello, World!"

@app.post("/post")
def post_action():
    return 'on Post'

@app.put("/put")
def put_action():
    return 'on Put'

@app.patch("/patch")
def patch_action():
    return 'on patch'

@app.delete("/delete")
def delete_action():
    return 'on delete'

@app.route("/get")
def head_action():
    return 'on get'

app.run(host='0.0.0.0', port=5000)
