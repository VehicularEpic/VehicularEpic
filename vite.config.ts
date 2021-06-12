import { join, resolve } from 'path'

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

export default defineConfig({
    plugins: [vue()],
    base: './',
    root: join(__dirname, 'web'),
    publicDir: join(__dirname, 'web', 'public'),
    build: {
        outDir: join(__dirname, 'dist')
    },
    resolve: {
        alias: {
            '@': resolve(__dirname, '/src')
        }
    }
});
