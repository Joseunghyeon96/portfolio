using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIEventOnKeyPress : MonoBehaviour
{
    public KeyCode key;
    private Button button;

    private void Awake()
    {
        button = GetComponent<Button>();
    }
    
    void Update()
    {
        if(Input.GetKeyDown(key))
        {
            button.onClick.Invoke();
        }
    }
}
