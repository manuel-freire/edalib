from os.path import isdir

# Where to find the sources
includes = ['src']

# Where to build the output
VariantDir('build', 'test', duplicate=0)

# How to build the demo
env = Environment(CPPFLAGS = '-g -Wall')
build_demo = env.Program('build/demo.exe',
    CPPPATH = includes, source = ['test/demo.cpp'])
Alias('build_demo', build_demo) 

# How to build the unit tests
env11 = Environment(CPPFLAGS = 
    '-g -Wall -std=c++11 -pedantic -Ibandit -Wno-unknown-pragmas ')
build_unit = env11.Program('build/unit.exe',  
    CPPPATH = includes, source = ['test/unit.cpp'])
env11.Depends('test/unit.o', 'get_bandit')
Alias('build_unit', build_unit) 

# Update option for bandit
AddOption('--update', dest='update', action='store_true',
          help='Update Bandit even if already present')

def getBandit(**kwargs):
    gitClone = "git clone -q --depth 1 "
    repoBase = "https://github.com/joakimkarlsson/"
    frameworksDir = "bandit/bandit/assertion_frameworks/"
    banditDir = isdir('bandit')
    if banditDir is False :
        print "downloading bandit unit-test library for the first time"
        env.Execute(gitClone + repoBase + "bandit")
        print "downloading snowhouse assertion library (bandit dependency)"
        env.Execute(gitClone + repoBase + "snowhouse")
        env.Execute("rmdir " + frameworksDir + "snowhouse")
        env.Execute("mv snowhouse " + frameworksDir)
    elif env.GetOption('update') :
        print "updating bandit unit-test library"
        env.Execute("cd bandit && git pull -q")
    else :
        print "bandit is available and no --update option was set"
    return None

# Download Bandit (if necessary; or freshen if requested)
env11.Command('get_bandit', [], getBandit)

# Build doc (if requested)
env.Command('doc', includes + ['doxyfile'], 
    'doxygen doxyfile')

# Execute tests (if requested)
env11.Command(
    'run_unit', [ build_unit, 'get_bandit' ] , 'build/unit.exe --reporter=spec');

# General usage help
Help("""
Type: 'scons' to build the integration tests,
      'scons build_unit' to also build unit tests (will download bandit)
      'scons run_unit' to also run the unit tests in pretty format
      'scons get_bandit' to download and/or update bandit      
      'scons doc' to regenerate documentation (requires doxygen)
      'scons -c all' to clean all generated files and folders
""")

# Cleanup
Clean('doc', 'doc')
Clean('all', ['bandit', 'doc', 'build'])

# The default build
Default(build_demo)
