const { join } = require('path');

require('ts-node').register();
require(join(__dirname, '..', 'app', 'main.ts'));
