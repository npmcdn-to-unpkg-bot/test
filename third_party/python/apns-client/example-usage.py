import os
import logging
logging.basicConfig()

from apnsclient import *

# Persistent connection for intensive messaging.
# Keep reference to session instance in some class static/global variable,
# otherwise it will be garbage collected and all connections will be closed.
session = Session()
con = session.get_connection("push_sandbox",
        cert_file=os.environ.get('APNS_CERT_FILE'),
        key_file=os.environ.get('APNS_KEY_FILE'))

# New message to 3 devices. You app will show badge 10 over app's icon.
message = Message(["ab113333 74c4bf4e 631456bc ed816458 824cf60a 59dbf28e 5652d3df 9bd31ef4"], alert="My message", badge=10)

# Send the message.
srv = APNs(con)
try:
    res = srv.send(message)
except:
    print "Can't connect to APNs, looks like network is down"
else:
    # Check failures. Check codes in APNs reference docs.
    for token, reason in res.failed.items():
        code, errmsg = reason
        # according to APNs protocol the token reported here
        # is garbage (invalid or empty), stop using and remove it.
        print "Device failed: {0}, reason: {1}".format(token, errmsg)

    # Check failures not related to devices.
    for code, errmsg in res.errors:
        print "Error: {}".format(errmsg)

    # Check if there are tokens that can be retried
    if res.needs_retry():
        # repeat with retry_message or reschedule your task
        retry_message = res.retry()