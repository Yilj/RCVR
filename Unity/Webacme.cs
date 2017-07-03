using UnityEngine;
using System.Collections;

public class Webcame : MonoBehaviour {
    private WebCamTexture webTexture;
    void Start()
    {
        WebCamDevice[] devices = WebCamTexture.devices;
        for (int i = 0; i < devices.Length; i++)
            Debug.Log(devices[i].name);
        webTexture = new WebCamTexture("SMI Grabber Device", 720, 480, 120);
        GetComponent<MeshRenderer>().material.mainTexture = webTexture;
        webTexture.Play();
     }
}
