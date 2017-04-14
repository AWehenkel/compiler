#!/usr/bin/env bash
for i in `seq 1 50`;
  do
    current_date_time="`date +%H`"
    current_date_time_1="`date +%M`
    say "il est "$current_date_time" heure et "$current_date_time_1" minutes"
  done
