/// <reference types="vite/client" />

declare module '*.vue' {
    import { DefineComponent } from 'vue'

    const Component: DefineComponent<{}, {}, any>
    export default Component;
}

declare const ipc: {

    on(event: string, listener: (...args: any[]) => void): typeof ipc;

    emit(event: string, ...args: any[]): typeof ipc;

};
