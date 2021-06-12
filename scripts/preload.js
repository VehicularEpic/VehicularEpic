const { contextBridge, ipcRenderer } = require('electron');

const on = (event, listener) => {
    ipcRenderer.on(event, (e, ...args) => listener(...args));
    return this;
};

const emit = (event, ...args) => {
    ipcRenderer.send(event, ...args);
    return true;
};

contextBridge.exposeInMainWorld('ipc', { on, emit });
