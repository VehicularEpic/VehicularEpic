import { join } from 'path';
import { app, ipcMain, BrowserWindow } from 'electron';

app.disableHardwareAcceleration();

app.whenReady().then(() => {
    const win = new BrowserWindow({
        webPreferences: {
            sandbox: true,
            offscreen: true,
            contextIsolation: true,
            preload: join(__dirname, '..', 'scripts', 'preload.js')
        },
        width: 1280,
        height: 720,
        useContentSize: true,
        transparent: true,
        show: false
    });

    if (app.isPackaged) {
        win.loadFile(join(__dirname, 'index.html'));
    } else {
        win.loadURL(process.env['VITE_DEV_SERVER'] as string)
            .then(() =>
                win.webContents.openDevTools({ mode: 'detach' })
            );
    }

    win.webContents.setWindowOpenHandler(() => ({ action: 'deny' }));

    win.webContents.setFrameRate(30);
});
