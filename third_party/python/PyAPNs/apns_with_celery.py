import time
import os
import sys
from apns import APNs, Frame, Payload
import logging
logging.basicConfig()

from celery import Celery, Task

app = Celery('apns_with_celery', backend='redis://localhost:6379/0', broker='redis://localhost:6379/0')

"""
$ export APNS_CERT_FILE= 
$ export APNS_KEY_FILE=
$ pip install -U celery[redis]

$ celery -A apns_with_celery worker --loglevel=debug 

"""

class CustomTask(Task):
    def __init__(self):
        self.apns = None
        self.id = None
    def run(self):
        if self.id is None:
            self.id = int(os.getpid())
        if self.apns is None:
            self.apns = APNs(use_sandbox=True,
                cert_file=os.environ.get('APNS_CERT_FILE'),
                key_file=os.environ.get('APNS_KEY_FILE'),
                enhanced=True)
        self.id = self.id + 1
        identifier = self.id
        payload = Payload(alert="This is from pid:{} " + str(os.getpid()) + " message", sound="default", badge=1)
        self.apns.gateway_server.send_notification('b998e50f19729f9e58a1967099e9e562ffe809adba78adef1844d76779923905', payload, identifier=identifier)