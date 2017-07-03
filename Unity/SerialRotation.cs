using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class SerialRotation : MonoBehaviour {

    privat SerialPort stream = new SerialPort("COM8", 9600);

    void Start()
    {
        stream.Open();
        stream.ReadTimeout = 25;
    }

    void Update()
    {
        string input = stream.ReadLine();
        string[] inputs = input.Split(',');
        float steering = int.Parse(inputs[0]);
        float gas = int.Parse(inputs[1]);
        GameObject.Find("AutoModel").GetComponent<AudioSource>().pitch = (180 - gas) / 180;
        steering = (steering - 240) / (30 - 240) * (270 - 90) + 180;
        transform.eulerAngles= new Vector3(steering, 180, 0);
        stream.BaseStream.Flush();
    }
}
