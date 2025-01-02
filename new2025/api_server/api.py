from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/payload1', methods=['GET','POST'])
def payload1():
    if request.method == 'GET':
        return "Web API"
    else:
        data = request.json
        timezone = data.get('timezone')

        if timezone:
            print(f'Receive timezone: {timezone}')



if __name__ == "__main__":
    app.run(port=5000, debug=True)