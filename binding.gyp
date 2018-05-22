{
  'targets': [
    {
      'target_name': 'compute-ranks-native',
      'sources': [ 'src/compute_ranks.cc', 'src/powerscore.cc' ],
      'include_dirs': ["<!@(node -p \"require('node-addon-api').include\")",
      '/usr/local/Cellar/eigen/3.3.4/include/eigen3/'],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'CLANG_CXX_LIBRARY': 'libc++',
        'MACOSX_DEPLOYMENT_TARGET': '10.7'
      },
      'msvs_settings': {
        'VCCLCompilerTool': { 'ExceptionHandling': 1 },
      }
    }
  ]
}