from flask import Flask, render_template
import socket

hostname = socket.gethostname()
IP = socket.gethostbyname(hostname)

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("test.html")

if __name__ == '__main__':
    app.run(host=IP, debug=True, port=8000)