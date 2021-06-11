#include <xfun.h>
#include <daemons.h>

inherit XFUN;
inherit COLOURUTIL_D;

private string _colour_basic_variable(mixed arg) {
  string colour;

  if( intp(arg) )          colour = "ired";
  else if( stringp(arg)  ) colour = "igreen";
  else if( objectp(arg)  ) colour = "iblue";
  else                     colour = "iwhite";

  return (string)call_other(this_object(), colour, variable_to_string(arg));
}

public string variable_to_string_colour(mixed variable) {
  int i, j, width;
  string output, *values;
  mixed key, *keys;

  if(pointerp(variable)) {
    values = ({});
    for(i=0; i<sizeof(variable); i++) {
      values += ({ variable_to_string_colour(variable[i]) });
    }
    output = imagenta("({") + implode(values, imagenta(", ")) + imagenta("})");
  } else if(mappingp(variable)) {
    width = m_width(variable);
    keys = m_indices(variable);
    output = icyan("([");
    for(i=0; i<sizeof(keys); i++) {
      key = keys[i];
      output += variable_to_string_colour(key);
      for(j=0; j<width; j++) {
        if(j==0)
          output += ": ";
        output += variable_to_string_colour(variable[key, j]);
        if( j < width - 1)
          output += "; ";
      }
      if( i < sizeof(keys) -1 )
        output += icyan(", ");
    }
    output += icyan("])");
  } else
    output = _colour_basic_variable(variable);

  return output;
}
