const { join } = require('path');
const { createServer } = require('vite');

const configFile = join(__dirname, '..', 'vite.config.ts');

createServer({ configFile })
    .then(server => server.listen())
    .then(({ httpServer }) => {
        const address = httpServer.address();

        process.env['VITE_DEV_SERVER'] = `http://${address.address}:${address.port}`;

        process.argv.push(join(__dirname, 'main.dev.js'));

        require('electron/cli');
    });
