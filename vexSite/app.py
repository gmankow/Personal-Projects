from flask import Flask, render_template
import socket

hostname = socket.gethostname()
IP = socket.gethostbyname(hostname)

app = Flask(__name__)

# Currently app.py doesn't work, to view pages use Live Server extension in VSCode on an html page

@app.route("/")
def home():
    return render_template("test.html")

if __name__ == '__main__':
    app.run(host=IP, debug=True, port=8000)