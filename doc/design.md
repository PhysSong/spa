# Design decisions

* Why not separate port and meta data?
  - The best way would have been to let each port have a pointer of
    port_meta_base. Getting a port's metadata would mean a second dispatch,
    which may have complicated too many things.
    Note that the metadata already tells the host what type it needs to
    provide (e.g. float*). If the plugin really wants to use the float
    differently, it is free to do so.
