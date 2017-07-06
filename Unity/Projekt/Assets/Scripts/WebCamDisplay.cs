using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WebCamDisplay : MonoBehaviour {
    
    void Start()
    {
        WebCamDevice[] webCamDevices = WebCamTexture.devices; // Make list of all available WebCam devices

        for (int i = 0; i < webCamDevices.Length; i++) // Debugging: Log name of all contected WebCam devices
            Debug.Log(webCamDevices[i].name);

        WebCamTexture webCamTexture = new WebCamTexture("SMI Grabber Device", 720, 480, 120); // Create new WebCamTexture and use "SMI Grabber Device" as input and set resolution to 720x480

        GetComponent<MeshRenderer>().material.mainTexture = webCamTexture; // Set windshield renderer texture to use WebCamTexture

        webCamTexture.Play(); // Start rendering WebCam image stream to windshield
    }
}
