import os
from flask import Flask
# from flask.ext.apns import APNS
from apnsclient import Session

app = Flask(__name__)
app.config['APNS_CERT_FILE'] = os.environ.get('APNS_CERT_FILE')
app.config['APNS_KEY_FILE'] = os.environ.get('APNS_CERT_FILE')
app.config['APNS_ADDRESS'] = 'push_sandbox'

session = Session()
# apns = APNS(app)

@app.route('/push/<token>')
def push(token):
    global session
    con = session.get_connection(app.config('APNS_ADDRESS'),
                                 cert_file=app.config['APNS_CERT_FILE'],
                                 key_file=app.config['APNS_KEY_FILE'])
    msg = Message([token], alert='My message', badge=3)
    sr = APNs(con)
    try:
        res = srv.send(message)
    except:
        print "Can't connect to APNs, network is down"
    else:
        for token, reason in res.failed.items():
            code, errmsg = reason
            print "Device failed:{0}, reason:{1}".format(token, errmsg)
        for code, errmsg in res.errors:
            print "Error: {}".format(errmsg)
    # apns.send_message([token], 'helloworld')

    return 'ok'

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')