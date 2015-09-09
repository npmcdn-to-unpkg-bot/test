import time
import os
from apns import APNs, Frame, Payload

apns = APNs(use_sandbox=True,
        cert_file=os.environ.get('APNS_CERT_FILE'),
        key_file=os.environ.get('APNS_KEY_FILE'))

# Send a notification
token_hex = 'ab11333374c4bf4e631456bced816458824cf60a59dbf28e5652d3df9bd31ef4'
payload = Payload(alert="Hello World!", sound="default", badge=1)
apns.gateway_server.send_notification(token_hex, payload)

# Send multiple notifications in a single transmission
# frame = Frame()
# identifier = 1
# expiry = time.time()+3600
# priority = 10
# frame.add_item('b5bb9d8014a0f9b1d61e21e796d78dccdf1352f23cd32812f4850b87', payload, identifier, expiry, priority)
# apns.gateway_server.send_notification_multiple(frame)