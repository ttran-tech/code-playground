from flask import Flask, request, jsonify

app = Flask(__name__)

action = {
    'encrypt': '53C82EBA31F6D416F331DE9162EBE997',
}

@app.route('/')
def index():
    return "<h3>It works!</h3>"

@app.route('/53C82EBA31F6D416F331DE9162EBE997', methods=['GET','POST'])
def encrypt_payload():
    if request.method == 'GET':
        return "Web API"
    else:
        data = request.json
        decrypted_key = data.get(action['encrypt'])

        if decrypted_key:
            print(f'Decrypted Key: {decrypted_key}')
        return "Data Received"



if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=True)