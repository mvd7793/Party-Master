package com.partyrock.element.lights;

import org.eclipse.swt.graphics.GC;

import com.partyrock.element.ElementSimulator;

public class LightSimulator extends ElementSimulator {
	private LightController controller;

	public LightSimulator(LightController controller) {
		super(controller);
		this.controller = controller;
	}

	@Override
	public void render(GC gc) {
		// TODO Auto-generated method stub

	}

	@Override
	public int getWidth() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int getHeight() {
		// TODO Auto-generated method stub
		return 0;
	}
}
