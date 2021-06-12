<template>
    <div class="space-y-2 w-1/3 p-2">
        <Button class="bg-white">Play</Button>
        <Button class="bg-white">Options</Button>
    </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'

import Button from '@/components/Button.vue'

export default defineComponent({
    name: 'MainMenu',
    components: { Button }
});
</script>
