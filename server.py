from flask import Flask
import json

app = Flask(__name__)

@app.route('/')
def hello_world():
    return "Hello world"

@app.route('/images/<artist>')
def artist_image(artist):
    return json.dumps({'artist': artist})

if __name__ == "__main__":
    app.run()
