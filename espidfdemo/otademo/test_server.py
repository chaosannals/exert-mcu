# pip install Flask

import os
from flask import Flask
from flask import send_from_directory

HERE = os.path.dirname(__file__)

app = Flask(__name__)

@app.route("/")
def index():
    return "Hello, World!"

# 固件本身启动后就会去拉去更新，然后拉去到不会更新的版本就停止更新了。
# 如果拉去的是自身，就会再次进入更新无穷无尽。
@app.route("/update", methods=["GET"])
def update_bin():
    # dir_path = os.path.join(HERE, 'build') # 这个是生成路径
    dir_path = HERE
    print(f"dir_path: {dir_path}") # 特意生成一个不会更新的版本。
    return send_from_directory(dir_path, 'otademo.bin', as_attachment=True)
    # return dir_path

app.run(host='0.0.0.0', port=5000)
