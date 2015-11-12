import time
import os
import sys
from apns import APNs, Frame, Payload
import logging
logging.basicConfig()

# config apns's logger
# logger = logging.getLogger("apns")
# stream_handler = logging.StreamHandler(sys.stderr)
# logger.addHandler(stream_handler)
# logger.setLevel(logging.DEBUG)

cert_file = os.environ.get('APNS_CERT_FILE')
key_file = os.environ.get('APNS_KEY_FILE')
if None in (cert_file, key_file):
    print 'Please export APNS_CERT_FILE=xxx'
    print 'Please export APNS_KEY_FILE=xxx'

    exit(1)

apns = APNs(use_sandbox=True,
        cert_file=cert_file,
        key_file=key_file,
        enhanced=True)

def response_listener(error):
    print 'Get error msg:' + str(error)

apns.gateway_server.register_response_listener(response_listener)

def send_notification(times=1, interval=None, start_identifier=100):
    start_time = time.time()
    # Send a notification
    for i in range(times):
        token_hex = '9b95bd9b60ef84a34777f6987163a8e4250e56d815232657284902ef3e78e5a6'
        identifier = start_identifier + i
        payload = Payload(alert="This is the " + str(i) + " message", sound="default", badge=i)
        apns.gateway_server.send_notification(token_hex, payload, identifier=identifier)
        print 'send over for identifier:', identifier
        if interval is not None:
            print 'sleep for ', interval, ' seconds...'
            time.sleep(interval)
    print 'Use time:{}'.format(time.time() - start_time)

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
    # send_notification(times=1, start_identifier=4294967291)
    # send_error_notification(times=1, start_identifier=4294967290)
    send_notification(times=1000, start_identifier=10000)
