// Function to insert customized MQTT Configuration actions
void custom_mqtt(String command, String cmd_value) {
    if ( command == "BckpRstr" ) {
        if (cmd_value == "") telnet_println("Restore data is empty");
        else {
            DeserializationError error = deserializeJson(config_doc, cmd_value); //Deserialize string to JSON data
            if (error) {telnet_print("JSON DeSerialization failure: "); telnet_println(error.f_str());}
            else {
                strcpy(config.DeviceName, config_doc["DeviceName"]);
                strcpy(config.Location, config_doc["Location"]);

                storage_write();
                bckp_rstr_flag = true;
                telnet_println("BckpRstr with success");
            }
        }
    }
    if ( command == "EFX") EFX = (byte)(cmd_value.toInt());
    if ( command == "Gain") { GAIN = (byte)(cmd_value.toInt()); telnet_println("New GAIN: " + String(GAIN));}
    if ( command == "Color")  HARGB_to_color(cmd_value);
    if ( command == "Light") {
        if ( SWITCH_Last == bool(cmd_value.toInt()) ) mqtt_publish(mqtt_pathtele, "Light", String(SWITCH));
        else SWITCH = bool(cmd_value.toInt());
    }


}
//  if ( command == "send_Telemetry" && bool(cmd_value.toInt())) { gps_update(); print_gps_data(); send_Telemetry(); }



void custom_update(){
    yield();
    //ambient_data();
    //mqtt_dump_data(mqtt_pathtele, "Telemetry");
    telnet_println("Color: " + String(Color) + " : GAIN: " + String(GAIN) + " : EFX: " + String(EFX));
    mqtt_publish(mqtt_pathtele, "Light", String(SWITCH));
    mqtt_publish(mqtt_pathtele, "Color", String(Color));
    mqtt_publish(mqtt_pathtele, "GAIN", String(GAIN));

}
