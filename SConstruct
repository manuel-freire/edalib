from os.path import isdir

# Setup build environment for unit-tests
env11 = Environment(CPPFLAGS = 
    '-g -Wall -std=c++11 -pedantic -Ibandit -Wno-unknown-pragmas ')

# Setup build environment for normal tests
env = Environment(CPPFLAGS = '-g -Wall')
includes = ['src']

# Download Bandit if necessary
AddOption('--update', dest='update', action='store_true')
bandit = isdir('bandit')
if (bandit is False) :
    print "downloading bandit unit-test library for the first time"
    env.Execute("git clone -q --depth 1 https://github.com/joakimkarlsson/bandit")
    print "downloading snowhouse assertion library (bandit dependency)"
    env.Execute("git clone -q --depth 1 https://github.com/joakimkarlsson/snowhouse")
    env.Execute("rmdir bandit/bandit/assertion_frameworks/snowhouse")
    env.Execute("mv snowhouse bandit/bandit/assertion_frameworks")
elif env.GetOption('update'):
    print "updating bandit unit-test library"
    env.Execute("cd bandit && git pull -q")

# Build tests
for name in ['test', 'unit'] :
    e = env11 if name.find('unit') >= 0 else env
    cpp = name + '.cpp'
    exe = name + '.exe'
    e.Program(exe, CPPPATH = includes, source = ['test/' + cpp])

