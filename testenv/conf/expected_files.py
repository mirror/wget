from difflib import unified_diff
import os
import sys
from conf import hook
from exc.test_failed import TestFailed


@hook()
class ExpectedFiles:
    def __init__(self, expected_fs):
        self.expected_fs = expected_fs

    @staticmethod
    def gen_local_fs_snapshot():
        snapshot = {}
        for parent, dirs, files in os.walk('.'):
            for name in files:
                f = {'content': ''}
                file_path = os.path.join(parent, name)
                with open(file_path) as fp:
                    f['content'] = fp.read()
                snapshot[file_path[2:]] = f

        return snapshot

    def __call__(self, test_obj):
        local_fs = self.gen_local_fs_snapshot()
        for file in self.expected_fs:
            if file.name in local_fs:
                local_file = local_fs.pop(file.name)
                if file.content != local_file['content']:
                    for line in unified_diff(local_file['content'],
                                             file.content,
                                             fromfile='Actual',
                                             tofile='Expected'):
                        print(line, file=sys.stderr)
                    raise TestFailed('Contents of %s do not match.' % file.name)
            else:
                raise TestFailed('Expected file %s not found.' % file.name)
        if local_fs:
            print(local_fs)
            raise TestFailed('Extra files downloaded.')
