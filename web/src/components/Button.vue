<template>
    <button
        @click.stop="click"
        class="hover:bg-opacity-20 bg-opacity-10 rounded focus:outline-none w-full h-8"
    >
        <div class="backdrop-filter backdrop-blur">
            <span class="text-white uppercase">
                <slot></slot>
            </span>
        </div>
    </button>
</template>

<script lang="ts">
import { defineComponent } from 'vue'

export default defineComponent({
    name: 'Button',
    methods: {
        click(e: Event) {
            this.$emit('click', e);
        }
    }
});
</script>
