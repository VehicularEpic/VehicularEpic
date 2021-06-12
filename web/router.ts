import VueRouter, { createRouter, createWebHistory } from 'vue-router'

import MainMenu from '@/views/MainMenu.vue'

const routes: VueRouter.RouteRecordRaw[] = [
    {
        path: '/',
        name: 'MainMenu',
        component: MainMenu
    }
];

const router = createRouter({ history: createWebHistory(), routes });
export default router;