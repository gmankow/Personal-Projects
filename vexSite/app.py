from flask import Flask, render_template
import socket

hostname = socket.gethostname()
IP = socket.gethostbyname(hostname)

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("home.html")

@app.route("/Our-Team")
def bios():
    return render_template("bios.html")



if __name__ == '__main__':
    app.run(host=IP, debug=True, port=8000)