#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# minimalmusicsetup_receivenest.py
#
# This file is part of NEST.
#
# Copyright (C) 2004 The NEST Initiative
#
# NEST is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# NEST is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NEST.  If not, see <http://www.gnu.org/licenses/>.

import nest

if not nest.ll_api.sli_func("statusdict/have_music ::"):
    import sys

    print("NEST was not compiled with support for MUSIC, not running.")
    sys.exit()

nest.set_verbosity("M_ERROR")

meip = nest.Create('music_event_in_proxy')
nest.SetStatus(meip, {'port_name': 'spikes_in', 'music_channel': 0})

n = nest.Create('iaf_psc_alpha')

nest.Connect(meip, n, 'one_to_one', {'weight': 750.0})

vm = nest.Create('voltmeter')
nest.SetStatus(vm, {'to_memory': False, 'to_screen': True})

nest.Connect(vm, n)

nest.Simulate(10)
