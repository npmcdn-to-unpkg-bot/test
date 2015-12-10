import argparse
import time
import os
import sys
from apns import APNs, Frame, Payload
import logging
logging.basicConfig()

# config apns's logger
logger = logging.getLogger("apns")
stream_handler = logging.StreamHandler(sys.stderr)
logger.addHandler(stream_handler)
logger.setLevel(logging.DEBUG)

_DEFAULT_PUSH_NUMBER = 100
_DEFAULT_PUSH_MESSAGE = 'this is the {} time pushing'
_DEFAULT_START_IDENTIFIER = 0
_DEFAULT_PUSH_INVTERVAL = 1

def get_certicate_from_environment():
    cert_file = os.environ.get('APNS_CERT_FILE')
    key_file = os.environ.get('APNS_KEY_FILE')
    if None in (cert_file, key_file):
        print 'Please use --cert_file or export APNS_CERT_FILE=xxx'
        print 'Please use --key_file  or export APNS_KEY_FILE=xxx'
        exit(1)
    return (cert_file, key_file)

def response_listener(error):
    print 'Get error msg:' + str(error)

def send_notification(token_hex=None,
        times=_DEFAULT_PUSH_NUMBER,
        interval=_DEFAULT_PUSH_INVTERVAL,
        start_identifier=_DEFAULT_START_IDENTIFIER,
        cert_file=None,
        key_file=None):
    # apns certificate files
    if None in (cert_file, key_file):
        (cert_file, key_file) = get_certicate_from_environment()

    # create apns
    apns = APNs(use_sandbox=True, cert_file=cert_file, key_file=key_file, enhanced=True)
    apns.gateway_server.register_response_listener(response_listener)

    start_time = time.time()
    # Send a notification
    for i in range(times):
        identifier = start_identifier + i
        payload = Payload(alert=_DEFAULT_PUSH_MESSAGE.format(i+1), sound="default", badge=i+1)
        apns.gateway_server.send_notification(token_hex, payload, identifier=identifier)
        print '> send over for identifier:<{}>'.format(identifier)
        if interval is not None:
            print '>  sleep for {} seconds...'.format(interval)
            time.sleep(interval)
    print '\n# Use time:{}\n'.format(time.time() - start_time)

def send_error_notification(times=1, start_identifier=0):
    """
    send error notification
    """
    def generate_fake_token(i):
        real_token = '9b95bd9b60ef84a34777f6987163a8e4250e56d815232657284902ef3e78e5a6'
        if i == 4:
            i = 1
        length = len(str(i))
        fake_token = real_token[:-len(str(i))] + str(i)
        assert len(fake_token) == len(real_token)
        return fake_token

    for i in range(0, times):
        token_hex = generate_fake_token(i)
        payload = Payload(alert="This is " + str(i) + " message", badge=i)
        apns.gateway_server.send_notification(token_hex, payload, identifier= start_identifier + i)
        print 'send over'

# Send multiple notifications in a single transmission
# frame = Frame()
# identifier = 1
# expiry = time.time()+3600
# priority = 10
# frame.add_item('b5bb9d8014a0f9b1d61e21e796d78dccdf1352f23cd32812f4850b87', payload, identifier, expiry, priority)
# apns.gateway_server.send_notification_multiple(frame)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('token', help='You must specify an token')
    parser.add_argument('-m', '--message', help='push message body, default "{}"'.format(_DEFAULT_PUSH_MESSAGE), default=_DEFAULT_PUSH_MESSAGE)
    parser.add_argument('-n', '--number', help='push times, default {}'.format(_DEFAULT_PUSH_NUMBER), type=int, default=_DEFAULT_PUSH_NUMBER)
    parser.add_argument('-i', '--identifier', help='start identifier, default {}'.format(_DEFAULT_START_IDENTIFIER), type=int, default=_DEFAULT_START_IDENTIFIER)
    parser.add_argument('-I', '--interval', help='push interval, default {} seconds'.format(_DEFAULT_PUSH_INVTERVAL), type=int, default=_DEFAULT_PUSH_INVTERVAL)
    parser.add_argument('--cert_file', help='apns cert file, you can also export APNS_CERT_FILE=xxx')
    parser.add_argument('--key_file', help='apns key file, you can also export APNS_KEY_FILE=xxx')

    args = parser.parse_args()

    send_notification(args.token, times=args.number,
            interval=args.interval,
            start_identifier=args.identifier,
            cert_file=args.cert_file,
            key_file=args.key_file)
