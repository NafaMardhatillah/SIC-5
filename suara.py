import json
from flask import Flask, request, jsonify

app = Flask(__name__)

sound_DATA = []

@app.route("/")
def root_route():
    return "Hello world!"

@app.route("/sound")
def get_sound():
    return jsonify(sound_DATA)

@app.route("/submit-sound", methods=["POST"])
def post_sound():
    pesan = request.data.decode("utf8")
    sound_DATA.append(float(pesan))
    print(pesan)
    return f"Received sound {pesan}"

@app.route("/submit", methods=["POST"])
def post_data():
    pesan = request.data.decode("utf8")
    pesan = json.loads(pesan)
    sound_DATA.append(float(pesan["sound"]))
    print(pesan)
    return f"Received data {pesan}"

if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0')
