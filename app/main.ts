import { join } from 'path';
import { app, BrowserWindow } from 'electron';

app.disableHardwareAcceleration();

app.whenReady().then(() => {
    const win = new BrowserWindow({
        webPreferences: {
            sandbox: true,
            offscreen: true
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
        win.loadURL(process.env['VITE_DEV_SERVER'] as string);
    }

    win.webContents.setWindowOpenHandler(() => ({ action: 'deny' }));

    win.webContents.setFrameRate(60);
});
