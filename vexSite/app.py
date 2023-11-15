from flask import Flask, render_template
import socket

hostname = socket.gethostname()
IP = socket.gethostbyname(hostname)

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("home.html")

@app.route("/OurLeads")
def bios():
    return render_template("bios.html")

@app.route("/ContactUs")
def contact():
    return render_template("contact.html")

@app.route("/Sponsors")
def sponsors():
    return render_template("sponsors.html")



if __name__ == '__main__':
    app.run(host=IP, debug=True, port=8000)