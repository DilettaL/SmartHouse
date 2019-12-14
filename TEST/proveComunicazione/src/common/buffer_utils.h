#pragma once
#define BUFFER_PUT(_IDX, _BSIZE_MAX)	\
  ++_IDX ## _end;					\
  if (_IDX ## _end>=_BSIZE_MAX)				\
    _IDX ## _end=0;					\
  ++_IDX ## _size;					
  
#define BUFFER_GET(_IDX, _BSIZE_MAX)	\
  ++_IDX ## _start;				\
  if (_IDX ## _start>=_BSIZE_MAX)		\
    _IDX ## _start =0;				\
  --_IDX ## _size;					
