using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class CarController : MonoBehaviour {

    public enum COM { COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8, COM9 }; // Enum of different possible arduino com ports

    public COM derPort = COM.COM1; // Variable to store cuttently selected port

    private SerialPort arduinoSerialPort; // Serial Port object

    void Start () {
        switch (derPort) // Construct serial port with selected com
        {
            case COM.COM1:
                arduinoSerialPort = new SerialPort("COM1", 9600);
                break;
            case COM.COM2:
                arduinoSerialPort = new SerialPort("COM2", 9600);
                break;
            case COM.COM3:
                arduinoSerialPort = new SerialPort("COM3", 9600);
                break;
            case COM.COM4:
                arduinoSerialPort = new SerialPort("COM4", 9600);
                break;
            case COM.COM5:
                arduinoSerialPort = new SerialPort("COM5", 9600);
                break;
            case COM.COM6:
                arduinoSerialPort = new SerialPort("COM6", 9600);
                break;
            case COM.COM7:
                arduinoSerialPort = new SerialPort("COM7", 9600);
                break;
            case COM.COM8:
                arduinoSerialPort = new SerialPort("COM8", 9600);
                break;
            case COM.COM9:
                arduinoSerialPort = new SerialPort("COM9", 9600);
                break;
            default:
                break;
        }

        arduinoSerialPort.Open(); // Start serial communication

        arduinoSerialPort.ReadTimeout = 25; // Set seial port read timout
    }
	
	void Update () {
        string input = arduinoSerialPort.ReadLine(); // Get input string from serial port

        string[] inputs = input.Split(','); // Split input string at ',' into two seperate values

        float steering = float.Parse(inputs[0]); // Parse first string into steering value

        float gas = float.Parse(inputs[1]); // Parse second string into gas value

        steering = steering.Remap(30, 240, 32, -32); // Remap steering to steering wheel angles

        transform.FindChild("steering_wheel").FindChild("model").transform.localRotation = Quaternion.Euler(steering, 0, 0); // Set steering wheel angle
        
        GetComponent<AudioSource>().pitch = (180 - gas) / 180; // Manipulate sound pitch with gas value
    }
}

public static class ExtensionMethods
{

    public static float Remap(this float value, float from1, float to1, float from2, float to2)
    {
        return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
    }

}