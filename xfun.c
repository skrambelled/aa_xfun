#pragma strict_types

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
          output += icyan(": ");
        output += variable_to_string_colour(variable[key, j]);
        if( j < width - 1)
          output += icyan("; ");
      }
      if( i < sizeof(keys) -1 )
        output += icyan(", ");
    }
    output += icyan("])");
  } else
    output = _colour_basic_variable(variable);

  return output;
}

private string my_month(string month_str) {
  switch(month_str) {
    case "Jan": return "01";
    case "Feb": return "02";
    case "Mar": return "03";
    case "Apr": return "04";
    case "May": return "05";
    case "Jun": return "06";
    case "Jul": return "07";
    case "Aug": return "08";
    case "Sep": return "09";
    case "Oct": return "10";
    case "Nov": return "11";
    case "Dec": return "12";
    default   : return "00";
  }
}

public string date_to_string(int time_) {
  string year, month, day;

  if(!time_)
    time_ = time();
 
  // collect our date info
  year  = ctime(time_)[20..<1];
  month = my_month(ctime(time_)[4..6]);
  day   = ctime(time_)[8..9];
    
  // account for whitespace in the day of the month int
  if(day[0..0] == " ")
    day[0..0] = "0";

  return year + month + day;
}