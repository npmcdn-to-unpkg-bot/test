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

apns = APNs(use_sandbox=True,
        cert_file=os.environ.get('APNS_CERT_FILE'),
        key_file=os.environ.get('APNS_KEY_FILE'),
        enhanced=True)

def response_listener(error):
    print 'Get error msg:' + str(error)
apns.gateway_server.register_response_listener(response_listener)

def send_notification(times=1, interval=None):
    # Send a notification
    for i in range(times):
        token_hex = 'ab11333374c4bf4e631456bced816458824cf60a59dbf28e5652d3df9bd31ef4'
        identifier = 100 + i
        payload = Payload(alert="This is the " + str(i) + " message", sound="default", badge=i)
        apns.gateway_server.send_notification(token_hex, payload, identifier=identifier)
        print 'send over for identifier:', identifier
        if interval is not None:
            print 'sleep for ', interval, ' seconds...'
            time.sleep(interval)

def send_error_notification(times=1):
    """
    send error notification
    """
    def generate_fake_token(i):
        real_token = 'ab11333374c4bf4e631456bced816458824cf60a59dbf28e5652d3df9bd31ef4'
        if i == 4:
            i = 1
        length = len(str(i))
        fake_token = real_token[:-len(str(i))] + str(i)
        assert len(fake_token) == len(real_token)
        return fake_token

    for i in range(0, times):
        token_hex = generate_fake_token(i)
        payload = Payload(alert="This is " + str(i) + " message", badge=i)
        apns.gateway_server.send_notification(token_hex, payload, identifier=i)
        print 'send over'

# Send multiple notifications in a single transmission
# frame = Frame()
# identifier = 1
# expiry = time.time()+3600
# priority = 10
# frame.add_item('b5bb9d8014a0f9b1d61e21e796d78dccdf1352f23cd32812f4850b87', payload, identifier, expiry, priority)
# apns.gateway_server.send_notification_multiple(frame)

if __name__ == '__main__':
    # send_notification(times=100 , interval=40)
    send_error_notification(times=3)
