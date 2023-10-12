from flask import Flask, render_template


app = Flask(__name__)

@app.route("/")
def home():
    return "<p>Test Home</p>"

if __name__ == '__main__':
    app.run(debug=True, port=8000)