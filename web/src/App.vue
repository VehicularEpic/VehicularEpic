<template>
    <div class="flex w-full h-full p-2">
        <router-view />
    </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'

export default defineComponent({
    name: 'App'
});
</script>
