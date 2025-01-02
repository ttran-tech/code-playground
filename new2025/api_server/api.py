from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/payload', methods=['GET','POST'])
def payload():
    if request.method == 'GET':
        return "Web API"
    else:
        data = request.json
        pid = data.get('pid')

        if pid:
            print(f'Receive pid: {pid}')
        return "Data Received"



if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=True)