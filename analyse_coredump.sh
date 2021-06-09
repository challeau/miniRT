#!/bin/sh

coredumpctl gdb $(coredumpctl list | tail -n1 | awk '{print $5}')
