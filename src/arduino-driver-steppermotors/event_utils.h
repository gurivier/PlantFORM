#ifndef EVENT_UTILS_HPP
#define EVENT_UTILS_HPP

#define PUSH_EVENT(_first, _last, _evt)  \
  if (_first == NULL) _first = _evt ;    \
  else _last->next = _evt ;              \
  _last = _evt ;                         \
  _evt->next = NULL ;

#define POP_EVENT(_type, _first)         \
  _type _tmp_event = _first->next ;      \
  free(_first) ;                         \
  _first = _tmp_event ;

#endif /* EVENT_UTILS_HPP */
