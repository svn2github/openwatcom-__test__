# Print preamble and set counter variable
BEGIN { 
    printf( "#define MSG_RC_BASE %d\n", rcbase )
    num = 1
    prev = ""
}

# Process all lines beginning with 'pick'
/^ *pick/ {
   gsub( /,/, "" ) # Remove commas
   if( prev == $2 )
      next         # Skip duplicates
   print "#define " $2 " (MSG_RC_BASE + " num ")"  
   num = num + 1   # Increment counter
   prev = $2
}

# Slightly different for lines beginning with 'wdpick'
/^ *wdpick/ {
   gsub( /,/, "" ) # Remove commas
   print "#define __" $2 " (MSG_RC_BASE + " num ")"  
   num = num + 1   # Increment counter
}
