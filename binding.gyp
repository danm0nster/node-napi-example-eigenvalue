{
    'targets': [
        {
            'target_name': 'compute-ranks-native',

            'sources': [ 'src/compute_ranks.cc', 'src/powerscore.cc' ],
            'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
            'cflags!': [ '-fno-exceptions' ],
            'cflags_cc!': [ '-fno-exceptions' ],
            'conditions':[
                ["OS=='linux'", {
                    "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")",
                                     '/usr/include/eigen3/'],
                }],
                ["OS=='mac'", {
                    "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")",
                                     '/usr/local/Cellar/eigen/3.3.4/include/eigen3/'],
                    'xcode_settings': {
                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                        'CLANG_CXX_LIBRARY': 'libc++',
                        'MACOSX_DEPLOYMENT_TARGET': '10.7'
                    },
                }],
                ["OS=='win'", {
                    "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
                    'msvs_settings': {
                        'VCCLCompilerTool': { 'ExceptionHandling': 1 },
                    },
                    }]
            ],
        }
    ]
}
