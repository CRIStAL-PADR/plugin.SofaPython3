# coding: utf8

import Sofa
import Sofa.Helper
import unittest

class Test(unittest.TestCase):
    def test_messages(self):
        """Test that the message are correctly sended and does not generates exceptions"""
        for fname in ["msg_info", "msg_warning", "msg_deprecated"]:
            f = getattr(Sofa.Helper, fname)
            f("Simple message")
            f("Emitter", "Simple message")
            f("Simple message with attached source info", "sourcefile.py", 10)
            f(Sofa.Core.Node("node"), "Simple message to an object")
            f(Sofa.Core.Node("node"), "Simple message to an object with attached source info", "sourcefile.py", 10)

