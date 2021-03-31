using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LoadSceneEvent : MonoBehaviour
{

    #region Sigleton
    private static LoadSceneEvent instance;
    public static LoadSceneEvent Instance
    {
        get
        {
            if (instance == null)
                instance = FindObjectOfType<LoadSceneEvent>();
            return instance;
        }
    }
    #endregion

    public List<GameObject> canvas;

    private void Awake()
    {
        Screen.SetResolution(1280, 720, false);
    }

    public void LoadScene(string sceneName)
    {
        SceneManager.LoadScene(sceneName);
    }
    
    public void LoadExitButton()
    {
        //UnityEditor.EditorApplication.isPlaying=false; 
        Application.Quit();
    }
    
    public void LoadButton(GameObject go)
    {
        foreach (GameObject w in canvas)
        {
            bool isActive = ((w.Equals(go)) ? true : false);
            if (isActive) w.SetActive((w.activeSelf) ? false : true);
            else w.SetActive(false);
        }
    }

    public void ShowCursor()
    {
        Cursor.lockState = CursorLockMode.None;
        Cursor.visible = true;
    }

    public void hideCursor()
    {
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
    }
}
