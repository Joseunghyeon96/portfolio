using System.Collections;
using System.Collections.Generic;
using System;
using System.IO;
using UnityEngine;


public class JsonManager<T>
{
    public string filename;

    public JsonManager(string filename)
    {
        this.filename = filename;
    }

    public bool Save(T data)
    {
        if (data == null) return false;
        try
        {
            File.WriteAllText(Application.dataPath + "/Data/" + filename, JsonUtility.ToJson(data));
            //Debug.Log("SAVE(" + filename + ") " + JsonUtility.ToJson(data));
            return true;
        }
        catch (Exception e)
        {
            Debug.LogException(e);
            return false;
        }
    }

    public bool Load(ref T data)
    {
        if (data == null) return false;
        try
        {
            data = JsonUtility.FromJson<T>(File.ReadAllText(Application.dataPath + "/Data/" + filename));
            //Debug.Log("LOAD(" + filename + ") " + JsonUtility.ToJson(data));
            return true;
        }
        catch (Exception e)
        {
            Debug.LogException(e);
            return false;
        }
    }
};